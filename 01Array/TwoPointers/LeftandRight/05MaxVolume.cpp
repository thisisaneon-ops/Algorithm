int MaxVolume(vector<int>& height)
{
    int left = 0;
    int right = height.size() - 1;
    int maxVol = 0;
    while(left < right)
    {
        int vol = (right - left) * min(height[left], height[right]);
        maxVol = max(maxVol, vol);
        if(height[left] > height[right])
        {
            right--;
        }
        else
        {
            left++;
        }
    }
    return maxVol;
}
